#include "../include/cylinder_bank_object.h"

#include "../include/engine_sim_application.h"

CylinderBankObject::CylinderBankObject() {
    m_bank = nullptr;
}

CylinderBankObject::~CylinderBankObject() {
    /* void */
}

void CylinderBankObject::generateGeometry() {
    GeometryGenerator *gen = m_app->getGeometryGenerator();

    const float lineWidth = (float)(m_bank->m_bore * 0.1);
    const float margin = lineWidth * 0.25f;
    const float dx = -(float)(m_bank->m_dy * (margin + m_bank->m_bore / 2 + lineWidth / 2));
    const float dy = (float)(m_bank->m_dx * (margin + m_bank->m_bore / 2 + lineWidth / 2));
    const float top_x = (float)(m_bank->m_dx * m_bank->m_deckHeight);
    const float top_y = (float)(m_bank->m_dy * m_bank->m_deckHeight);
    const float bottom_x = (float)(m_bank->m_dx * (0.4 * m_bank->m_deckHeight));
    const float bottom_y = (float)(m_bank->m_dy * (0.4 * m_bank->m_deckHeight));

    GeometryGenerator::Line2dParameters params;
    params.lineWidth = lineWidth;

    GeometryGenerator::Circle2dParameters circleParams;
    circleParams.radius = lineWidth / 2.0f;
    circleParams.maxEdgeLength = m_app->pixelsToUnits(5.0f);

    gen->startShape();

    params.x0 = top_x + dx;
    params.y0 = top_y + dy;
    params.x1 = bottom_x + dx;
    params.y1 = bottom_y + dy;
    gen->generateLine2d(params);

    circleParams.center_x = params.x1;
    circleParams.center_y = params.y1;
    gen->generateCircle2d(circleParams);

    params.x0 = top_x - dx;
    params.y0 = top_y - dy;
    params.x1 = bottom_x - dx;
    params.y1 = bottom_y - dy;
    gen->generateLine2d(params);

    circleParams.center_x = params.x1;
    circleParams.center_y = params.y1;
    gen->generateCircle2d(circleParams);

    gen->endShape(&m_walls);
}

void CylinderBankObject::render(const ViewParameters *view) {
    resetShader();

    const ysVector col = ysMath::Add(
        ysMath::Mul(ysMath::Constants::One, ysMath::LoadScalar(0.01f)),
        ysMath::Mul(m_app->getBackgroundColor(), ysMath::LoadScalar(0.99f))
    );

    m_app->getShaders()->SetBaseColor(m_app->getPink());
    m_app->drawGenerated(m_walls, 0x10);
}

void CylinderBankObject::process(float dt) {
    /* void */
}

void CylinderBankObject::destroy() {
    /* void */
}